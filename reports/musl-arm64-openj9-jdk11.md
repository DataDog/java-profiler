---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 04:45:07 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1054 |
| Sample Rate | 17.57/sec |
| Health Score | 1098% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1790325642 22
1790325647 22
1790325652 22
1790325657 22
1790325662 22
1790325667 22
1790325672 22
1790325677 22
1790325683 22
1790325688 22
1790325693 22
1790325698 22
1790325703 22
1790325708 22
1790325713 27
1790325718 27
1790325723 27
1790325728 27
1790325733 27
1790325738 27
```
</details>

---

