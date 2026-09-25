---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 00:58:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 15 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1790312079 22
1790312084 22
1790312089 22
1790312094 22
1790312099 22
1790312104 22
1790312109 22
1790312114 22
1790312119 22
1790312124 22
1790312129 22
1790312134 22
1790312139 22
1790312144 22
1790312149 22
1790312154 22
1790312159 22
1790312164 22
1790312169 22
1790312174 22
```
</details>

---

