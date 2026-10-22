---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 10:29:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 11 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1792679085 48
1792679090 48
1792679095 48
1792679100 48
1792679105 48
1792679110 48
1792679115 48
1792679120 48
1792679125 48
1792679130 48
1792679135 48
1792679140 48
1792679145 48
1792679150 48
1792679155 48
1792679160 36
1792679165 36
1792679170 36
1792679175 36
1792679180 36
```
</details>

---

