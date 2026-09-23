---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 05:40:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 45-71 cores)</summary>

```
1790156145 45
1790156150 45
1790156155 45
1790156160 45
1790156165 45
1790156170 45
1790156175 45
1790156180 45
1790156185 45
1790156190 45
1790156195 45
1790156200 45
1790156205 45
1790156210 45
1790156215 45
1790156220 47
1790156225 47
1790156230 47
1790156235 47
1790156240 71
```
</details>

---

