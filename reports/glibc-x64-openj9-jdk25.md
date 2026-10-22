---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 08:00:06 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1792670132 28
1792670137 28
1792670142 28
1792670147 28
1792670152 28
1792670157 28
1792670162 28
1792670167 28
1792670172 28
1792670177 28
1792670182 28
1792670187 28
1792670192 28
1792670197 28
1792670202 28
1792670207 28
1792670212 28
1792670217 28
1792670222 28
1792670227 30
```
</details>

---

