---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 05:52:46 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 55-61 cores)</summary>

```
1795690117 55
1795690122 61
1795690127 61
1795690132 59
1795690137 59
1795690142 59
1795690147 59
1795690152 59
1795690157 59
1795690162 59
1795690167 59
1795690172 59
1795690177 59
1795690182 59
1795690187 59
1795690192 59
1795690197 59
1795690202 59
1795690207 59
1795690212 59
```
</details>

---

