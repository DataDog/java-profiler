---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-15 17:55:42 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 58-67 cores)</summary>

```
1792100832 63
1792100837 58
1792100842 58
1792100847 58
1792100852 58
1792100857 58
1792100862 62
1792100867 62
1792100872 62
1792100877 62
1792100882 62
1792100887 62
1792100892 62
1792100897 62
1792100902 62
1792100907 62
1792100912 62
1792100917 62
1792100922 62
1792100927 62
```
</details>

---

