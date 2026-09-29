---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 00:59:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 85-96 cores)</summary>

```
1790657680 96
1790657685 96
1790657690 96
1790657695 96
1790657700 96
1790657705 96
1790657710 96
1790657715 96
1790657720 96
1790657725 96
1790657730 96
1790657735 96
1790657740 96
1790657745 85
1790657750 85
1790657755 85
1790657760 85
1790657765 85
1790657770 85
1790657775 85
```
</details>

---

