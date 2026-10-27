---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 16:51:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793133891 43
1793133896 43
1793133901 43
1793133906 43
1793133911 43
1793133916 43
1793133921 43
1793133926 43
1793133931 43
1793133936 43
1793133941 43
1793133946 43
1793133951 43
1793133956 46
1793133961 46
1793133966 46
1793133971 46
1793133976 46
1793133981 48
1793133986 48
```
</details>

---

