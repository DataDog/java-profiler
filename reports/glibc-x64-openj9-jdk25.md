---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:15:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1794582701 70
1794582706 70
1794582711 70
1794582716 72
1794582721 72
1794582726 72
1794582731 72
1794582736 72
1794582741 72
1794582746 72
1794582751 72
1794582756 72
1794582761 72
1794582766 72
1794582771 72
1794582776 72
1794582781 72
1794582786 72
1794582791 72
1794582796 72
```
</details>

---

