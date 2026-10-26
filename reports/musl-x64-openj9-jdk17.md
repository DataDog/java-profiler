---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-26 10:05:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793023151 30
1793023156 30
1793023161 30
1793023166 30
1793023171 30
1793023176 30
1793023181 30
1793023186 30
1793023191 32
1793023196 32
1793023201 32
1793023207 32
1793023212 30
1793023217 30
1793023222 30
1793023227 30
1793023232 30
1793023237 30
1793023242 30
1793023247 30
```
</details>

---

