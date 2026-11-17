---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:48:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 70-76 cores)</summary>

```
1794930069 70
1794930074 70
1794930079 70
1794930084 72
1794930089 72
1794930094 72
1794930099 72
1794930104 72
1794930109 72
1794930115 72
1794930120 74
1794930125 74
1794930130 76
1794930135 76
1794930140 76
1794930145 76
1794930150 76
1794930155 76
1794930160 76
1794930165 76
```
</details>

---

