---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:36:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794594664 40
1794594669 40
1794594674 40
1794594679 40
1794594684 40
1794594689 40
1794594694 40
1794594699 40
1794594704 40
1794594709 40
1794594714 40
1794594719 40
1794594724 40
1794594729 40
1794594734 35
1794594739 35
1794594744 35
1794594749 35
1794594754 35
1794594759 35
```
</details>

---

