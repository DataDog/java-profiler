---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:35:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 12 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794508143 48
1794508148 48
1794508153 48
1794508158 48
1794508163 48
1794508168 48
1794508173 48
1794508178 48
1794508183 48
1794508188 48
1794508193 48
1794508198 48
1794508203 48
1794508208 48
1794508213 48
1794508218 48
1794508223 48
1794508228 48
1794508233 48
1794508238 48
```
</details>

---

