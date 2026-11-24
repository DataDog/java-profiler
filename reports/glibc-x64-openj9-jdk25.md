---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 05:51:09 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1795517181 87
1795517186 87
1795517191 87
1795517196 87
1795517201 87
1795517206 87
1795517211 87
1795517216 87
1795517221 87
1795517227 87
1795517232 87
1795517237 87
1795517242 85
1795517247 85
1795517252 85
1795517257 85
1795517262 85
1795517267 85
1795517272 85
1795517277 85
```
</details>

---

