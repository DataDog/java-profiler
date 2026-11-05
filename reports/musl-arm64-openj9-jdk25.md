---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 09:37:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 11 |
| Allocations | 176 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1793889092 48
1793889097 48
1793889102 48
1793889107 42
1793889112 42
1793889117 42
1793889122 42
1793889127 43
1793889132 43
1793889137 43
1793889142 43
1793889147 43
1793889152 43
1793889157 43
1793889162 48
1793889167 48
1793889172 45
1793889177 45
1793889182 45
1793889187 45
```
</details>

---

