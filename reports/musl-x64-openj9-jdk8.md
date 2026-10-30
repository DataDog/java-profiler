---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-30 09:45:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1793367638 61
1793367643 61
1793367648 61
1793367653 61
1793367658 61
1793367663 61
1793367668 61
1793367673 61
1793367678 61
1793367683 59
1793367688 59
1793367693 59
1793367698 59
1793367703 59
1793367708 59
1793367713 59
1793367718 61
1793367723 61
1793367728 59
1793367733 59
```
</details>

---

