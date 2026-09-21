---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 09:40:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 7 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789997720 48
1789997725 48
1789997730 48
1789997735 48
1789997740 48
1789997745 43
1789997750 43
1789997755 43
1789997760 43
1789997765 43
1789997770 43
1789997775 43
1789997780 43
1789997785 43
1789997790 43
1789997795 48
1789997800 48
1789997805 48
1789997810 48
1789997815 48
```
</details>

---

