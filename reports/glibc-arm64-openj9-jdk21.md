---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 10:29:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 6-18 cores)</summary>

```
1792679063 6
1792679068 6
1792679073 6
1792679078 18
1792679083 18
1792679088 18
1792679093 18
1792679098 18
1792679103 18
1792679108 18
1792679113 18
1792679118 18
1792679123 18
1792679128 18
1792679133 18
1792679138 18
1792679143 18
1792679148 18
1792679153 18
1792679158 18
```
</details>

---

