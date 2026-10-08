---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-08 09:45:21 EDT

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
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 14 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (2 unique values: 40-43 cores)</summary>

```
1791466765 40
1791466770 40
1791466775 40
1791466780 40
1791466785 43
1791466790 43
1791466795 43
1791466800 43
1791466805 43
1791466810 43
1791466815 43
1791466820 43
1791466825 43
1791466830 43
1791466835 43
1791466840 43
1791466845 43
1791466850 43
1791466855 43
1791466860 43
```
</details>

---

