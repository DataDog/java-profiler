---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 00:07:38 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (5 unique values: 54-77 cores)</summary>

```
1794546147 54
1794546152 54
1794546157 54
1794546162 54
1794546167 54
1794546172 54
1794546177 54
1794546182 71
1794546187 71
1794546192 71
1794546197 73
1794546202 73
1794546207 73
1794546212 75
1794546217 75
1794546222 77
1794546227 77
1794546233 77
1794546238 77
1794546243 75
```
</details>

---

