---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 05:40:12 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (4 unique values: 40-47 cores)</summary>

```
1790156084 47
1790156089 46
1790156094 46
1790156099 46
1790156104 46
1790156109 46
1790156114 46
1790156119 46
1790156124 42
1790156129 42
1790156134 40
1790156139 40
1790156144 40
1790156149 40
1790156154 40
1790156159 40
1790156164 46
1790156169 46
1790156174 46
1790156179 46
```
</details>

---

