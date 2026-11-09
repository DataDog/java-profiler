---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-11-09 17:14:00 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 25-25 cores)</summary>

```
1794262132 25
1794262137 25
1794262142 25
1794262147 25
1794262152 25
1794262157 25
1794262162 25
1794262167 25
1794262172 25
1794262177 25
1794262182 25
1794262187 25
1794262192 25
1794262197 25
1794262202 25
1794262207 25
1794262212 25
1794262217 25
1794262222 25
1794262227 25
```
</details>

---

