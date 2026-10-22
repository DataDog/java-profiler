---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 08:46:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 30-63 cores)</summary>

```
1792672897 47
1792672902 47
1792672907 47
1792672912 47
1792672917 47
1792672922 63
1792672927 63
1792672932 63
1792672937 63
1792672942 63
1792672947 63
1792672952 63
1792672957 63
1792672962 63
1792672967 63
1792672972 63
1792672977 63
1792672982 63
1792672987 63
1792672992 63
```
</details>

---

