---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 00:07:37 EST

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
| CPU Cores (end) | 48 |
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
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794546161 48
1794546166 48
1794546172 48
1794546177 48
1794546182 48
1794546187 48
1794546192 48
1794546197 48
1794546202 48
1794546207 48
1794546212 43
1794546217 43
1794546222 43
1794546227 43
1794546232 43
1794546237 43
1794546242 43
1794546247 43
1794546252 48
1794546257 48
```
</details>

---

