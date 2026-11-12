---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:37:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1100 |
| Sample Rate | 18.33/sec |
| Health Score | 1146% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 76-83 cores)</summary>

```
1794508149 78
1794508154 78
1794508159 78
1794508164 78
1794508169 78
1794508174 76
1794508179 76
1794508184 76
1794508189 76
1794508194 76
1794508199 76
1794508204 76
1794508209 76
1794508214 76
1794508219 76
1794508224 80
1794508229 80
1794508234 80
1794508239 80
1794508244 80
```
</details>

---

