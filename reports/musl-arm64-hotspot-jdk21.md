---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:56:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 14 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1793616724 31
1793616729 31
1793616734 31
1793616739 31
1793616744 31
1793616749 31
1793616754 31
1793616759 31
1793616764 31
1793616769 31
1793616774 31
1793616779 31
1793616784 31
1793616789 31
1793616794 31
1793616799 31
1793616804 31
1793616809 31
1793616814 31
1793616819 31
```
</details>

---

