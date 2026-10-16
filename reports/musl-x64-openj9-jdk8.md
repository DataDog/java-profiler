---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-16 05:53:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 224 |
| Sample Rate | 3.73/sec |
| Health Score | 233% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1792144091 40
1792144096 40
1792144101 40
1792144106 40
1792144111 40
1792144116 40
1792144121 40
1792144126 40
1792144131 40
1792144136 40
1792144141 40
1792144146 40
1792144151 40
1792144156 40
1792144161 42
1792144166 42
1792144171 42
1792144176 42
1792144181 42
1792144186 42
```
</details>

---

