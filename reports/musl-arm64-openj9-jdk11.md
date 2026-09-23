---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:48:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 11 |
| Allocations | 181 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 38-64 cores)</summary>

```
1790171066 38
1790171071 38
1790171076 38
1790171081 38
1790171086 38
1790171091 38
1790171096 38
1790171101 38
1790171106 38
1790171111 38
1790171116 38
1790171121 38
1790171126 38
1790171131 38
1790171136 45
1790171141 45
1790171146 45
1790171152 45
1790171157 45
1790171162 45
```
</details>

---

