---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 09:36:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 8 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 11 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792416546 51
1792416551 51
1792416556 51
1792416561 51
1792416566 51
1792416571 51
1792416576 51
1792416581 51
1792416586 64
1792416591 64
1792416596 64
1792416601 64
1792416606 64
1792416611 64
1792416616 64
1792416621 64
1792416626 64
1792416631 64
1792416636 64
1792416641 64
```
</details>

---

