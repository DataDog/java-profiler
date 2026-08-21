---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 15:09:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787339113 64
1787339118 64
1787339123 64
1787339128 64
1787339133 64
1787339138 64
1787339143 64
1787339148 64
1787339153 64
1787339158 64
1787339163 64
1787339168 64
1787339173 64
1787339178 64
1787339183 64
1787339188 64
1787339193 64
1787339198 64
1787339203 64
1787339208 64
```
</details>

---

