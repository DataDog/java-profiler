---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-12 13:12:34 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 11 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1114 |
| Sample Rate | 18.57/sec |
| Health Score | 1161% |
| Threads | 13 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 82-87 cores)</summary>

```
1770919633 84
1770919638 82
1770919643 82
1770919648 82
1770919653 82
1770919658 82
1770919663 82
1770919668 82
1770919673 82
1770919678 82
1770919683 82
1770919688 82
1770919693 82
1770919698 82
1770919703 82
1770919708 82
1770919713 84
1770919718 84
1770919723 84
1770919728 82
```
</details>

---

