---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:54:46 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 11 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (1 unique values: 10-10 cores)</summary>

```
1793800132 10
1793800137 10
1793800142 10
1793800147 10
1793800152 10
1793800157 10
1793800162 10
1793800167 10
1793800172 10
1793800177 10
1793800182 10
1793800187 10
1793800192 10
1793800197 10
1793800202 10
1793800207 10
1793800212 10
1793800217 10
1793800222 10
1793800227 10
```
</details>

---

