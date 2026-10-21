---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 17:49:34 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (2 unique values: 24-27 cores)</summary>

```
1792619108 24
1792619113 24
1792619118 24
1792619123 24
1792619128 24
1792619133 24
1792619138 24
1792619143 24
1792619148 24
1792619153 24
1792619158 24
1792619163 24
1792619168 24
1792619173 24
1792619178 27
1792619183 27
1792619188 27
1792619193 27
1792619198 27
1792619203 27
```
</details>

---

