---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-23 00:55:51 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1787460704 61
1787460709 61
1787460714 61
1787460719 61
1787460724 61
1787460729 59
1787460734 59
1787460739 59
1787460744 59
1787460749 59
1787460754 59
1787460759 59
1787460764 59
1787460769 59
1787460774 59
1787460779 61
1787460784 61
1787460789 61
1787460794 61
1787460799 61
```
</details>

---

