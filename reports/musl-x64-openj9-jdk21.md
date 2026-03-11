---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 13:17:32 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 12 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1773249148 59
1773249153 59
1773249158 59
1773249163 59
1773249168 59
1773249173 59
1773249178 59
1773249183 59
1773249188 59
1773249193 59
1773249198 59
1773249203 57
1773249208 57
1773249213 57
1773249218 57
1773249223 57
1773249228 57
1773249233 57
1773249238 57
1773249243 57
```
</details>

---

