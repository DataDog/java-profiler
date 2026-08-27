---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-27 09:40:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 39-44 cores)</summary>

```
1787837739 39
1787837744 44
1787837749 44
1787837754 44
1787837759 44
1787837764 44
1787837769 44
1787837774 44
1787837779 44
1787837784 44
1787837789 44
1787837794 44
1787837799 44
1787837804 44
1787837809 44
1787837814 44
1787837819 44
1787837824 44
1787837829 44
1787837834 39
```
</details>

---

