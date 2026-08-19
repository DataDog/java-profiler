---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 11:07:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1787151759 35
1787151764 35
1787151769 35
1787151774 35
1787151780 35
1787151785 35
1787151790 35
1787151795 35
1787151800 40
1787151805 40
1787151810 40
1787151815 40
1787151820 40
1787151825 40
1787151830 40
1787151835 40
1787151840 40
1787151845 40
1787151850 40
1787151855 40
```
</details>

---

