---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 11:32:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (5 unique values: 68-76 cores)</summary>

```
1795192113 76
1795192118 76
1795192123 76
1795192128 74
1795192133 74
1795192138 74
1795192143 74
1795192148 72
1795192153 72
1795192158 72
1795192163 72
1795192168 70
1795192173 70
1795192178 70
1795192183 70
1795192188 70
1795192193 70
1795192198 70
1795192203 70
1795192208 70
```
</details>

---

