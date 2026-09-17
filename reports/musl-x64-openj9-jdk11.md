---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:02:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1031 |
| Sample Rate | 17.18/sec |
| Health Score | 1074% |
| Threads | 11 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1789682091 83
1789682096 83
1789682101 83
1789682106 83
1789682111 83
1789682116 81
1789682121 81
1789682126 81
1789682131 81
1789682136 81
1789682141 81
1789682146 81
1789682151 81
1789682156 81
1789682161 81
1789682166 81
1789682171 81
1789682176 81
1789682181 81
1789682186 81
```
</details>

---

