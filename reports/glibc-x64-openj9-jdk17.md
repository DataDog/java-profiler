---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-02 09:31:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (6 unique values: 46-56 cores)</summary>

```
1770042125 55
1770042130 55
1770042135 55
1770042140 55
1770042145 51
1770042150 51
1770042155 51
1770042160 51
1770042165 56
1770042170 56
1770042175 52
1770042180 52
1770042185 52
1770042190 52
1770042195 52
1770042200 52
1770042205 52
1770042210 52
1770042215 46
1770042220 46
```
</details>

---

