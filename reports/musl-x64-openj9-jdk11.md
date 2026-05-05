---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-05 06:30:02 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 9 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1777976668 45
1777976673 45
1777976678 45
1777976683 45
1777976688 45
1777976693 45
1777976698 45
1777976703 45
1777976708 45
1777976713 45
1777976718 45
1777976723 45
1777976728 42
1777976733 42
1777976738 42
1777976743 42
1777976748 42
1777976753 42
1777976758 40
1777976763 40
```
</details>

---

