---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-15 17:55:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 8 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 71-92 cores)</summary>

```
1792100847 92
1792100852 92
1792100857 92
1792100862 92
1792100867 71
1792100872 71
1792100877 71
1792100882 71
1792100887 71
1792100892 71
1792100897 71
1792100902 71
1792100907 71
1792100912 71
1792100917 71
1792100922 71
1792100927 71
1792100932 71
1792100937 71
1792100942 71
```
</details>

---

