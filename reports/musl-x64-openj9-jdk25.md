---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 06:08:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 12 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 74-93 cores)</summary>

```
1794827017 87
1794827022 87
1794827027 87
1794827032 87
1794827037 87
1794827042 87
1794827047 87
1794827052 87
1794827057 87
1794827062 87
1794827067 87
1794827072 87
1794827077 87
1794827082 87
1794827087 87
1794827092 87
1794827097 87
1794827102 93
1794827107 93
1794827112 93
```
</details>

---

