---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-05 06:30:02 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 70-77 cores)</summary>

```
1777976668 76
1777976673 76
1777976678 72
1777976683 72
1777976688 72
1777976693 72
1777976698 72
1777976703 70
1777976709 70
1777976714 72
1777976719 72
1777976724 72
1777976729 72
1777976734 72
1777976739 72
1777976744 72
1777976749 73
1777976754 73
1777976759 77
1777976764 77
```
</details>

---

