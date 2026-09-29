---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 00:59:54 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1790657684 79
1790657689 79
1790657694 79
1790657699 81
1790657704 81
1790657709 81
1790657714 81
1790657719 81
1790657724 81
1790657729 81
1790657734 81
1790657739 81
1790657744 81
1790657749 81
1790657754 81
1790657759 81
1790657764 81
1790657769 81
1790657774 81
1790657779 81
```
</details>

---

