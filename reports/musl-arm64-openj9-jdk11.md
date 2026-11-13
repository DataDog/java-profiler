---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:15:30 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 35 |
| Sample Rate | 0.58/sec |
| Health Score | 36% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794582671 48
1794582676 48
1794582681 48
1794582686 48
1794582691 48
1794582696 48
1794582701 48
1794582706 48
1794582711 48
1794582716 48
1794582721 48
1794582726 48
1794582731 48
1794582736 48
1794582741 48
1794582746 48
1794582751 48
1794582757 48
1794582762 48
1794582767 48
```
</details>

---

