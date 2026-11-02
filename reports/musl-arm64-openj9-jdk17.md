---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 05:56:17 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 13 |
| Allocations | 100 |

<details>
<summary>CPU Timeline (2 unique values: 24-36 cores)</summary>

```
1793616709 24
1793616714 36
1793616719 36
1793616724 36
1793616729 36
1793616734 36
1793616739 36
1793616744 36
1793616749 36
1793616754 36
1793616759 36
1793616764 36
1793616769 36
1793616774 36
1793616779 36
1793616784 36
1793616789 36
1793616794 36
1793616799 36
1793616804 36
```
</details>

---

