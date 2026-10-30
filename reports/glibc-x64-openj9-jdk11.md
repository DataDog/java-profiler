---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 06:16:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793355123 32
1793355128 32
1793355133 32
1793355138 32
1793355143 32
1793355148 32
1793355153 32
1793355158 32
1793355163 32
1793355168 32
1793355173 32
1793355178 32
1793355183 32
1793355188 32
1793355193 32
1793355198 32
1793355203 32
1793355208 32
1793355213 32
1793355218 32
```
</details>

---

