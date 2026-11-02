---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-01 20:28:11 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 11 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 9 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793582656 40
1793582661 40
1793582666 40
1793582671 40
1793582676 40
1793582681 40
1793582686 40
1793582691 40
1793582696 40
1793582701 40
1793582706 40
1793582711 40
1793582716 40
1793582721 40
1793582726 40
1793582731 40
1793582736 40
1793582741 40
1793582746 40
1793582751 40
```
</details>

---

