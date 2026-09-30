---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:59:10 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 80-90 cores)</summary>

```
1790780027 90
1790780032 82
1790780037 82
1790780042 82
1790780047 82
1790780052 82
1790780057 82
1790780062 82
1790780067 82
1790780072 82
1790780077 82
1790780082 82
1790780087 82
1790780092 85
1790780097 85
1790780102 85
1790780107 85
1790780112 85
1790780117 85
1790780122 85
```
</details>

---

