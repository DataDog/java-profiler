---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-27 09:00:59 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 14.20/sec |
| Health Score | 887% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 24.03/sec |
| Health Score | 1502% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 19-31 cores)</summary>

```
1769514142 28
1769514147 28
1769514152 28
1769514157 28
1769514162 28
1769514167 28
1769514172 28
1769514177 19
1769514182 19
1769514187 19
1769514192 19
1769514197 19
1769514202 19
1769514207 19
1769514212 19
1769514217 19
1769514222 19
1769514227 19
1769514232 19
1769514237 19
```
</details>

---

