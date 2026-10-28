---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:17:16 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 11 |
| Allocations | 199 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1793185629 64
1793185634 64
1793185639 51
1793185644 51
1793185649 51
1793185654 51
1793185659 51
1793185664 51
1793185669 51
1793185675 51
1793185680 51
1793185685 51
1793185690 51
1793185695 51
1793185700 51
1793185705 51
1793185710 51
1793185715 51
1793185720 51
1793185725 51
```
</details>

---

