---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:16:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1794582666 82
1794582671 82
1794582676 82
1794582681 82
1794582686 84
1794582691 84
1794582696 84
1794582701 84
1794582706 84
1794582711 84
1794582716 84
1794582721 84
1794582726 84
1794582731 84
1794582736 84
1794582741 84
1794582746 86
1794582751 86
1794582756 86
1794582761 86
```
</details>

---

