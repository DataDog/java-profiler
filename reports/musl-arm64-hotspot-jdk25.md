---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:27:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 11 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794428579 51
1794428584 49
1794428589 49
1794428594 49
1794428599 49
1794428604 49
1794428609 49
1794428614 49
1794428619 49
1794428624 51
1794428629 51
1794428634 51
1794428639 51
1794428644 51
1794428649 51
1794428654 51
1794428659 51
1794428664 51
1794428669 51
1794428674 51
```
</details>

---

