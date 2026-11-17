---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:58:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 60-67 cores)</summary>

```
1794930688 60
1794930693 60
1794930698 60
1794930703 60
1794930708 60
1794930713 60
1794930718 60
1794930723 62
1794930728 62
1794930733 62
1794930738 62
1794930743 62
1794930748 62
1794930753 62
1794930758 62
1794930763 62
1794930768 62
1794930773 62
1794930778 62
1794930783 62
```
</details>

---

