---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 16:34:00 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777321743 64
1777321748 64
1777321753 64
1777321758 64
1777321763 64
1777321768 64
1777321773 64
1777321778 64
1777321783 64
1777321788 64
1777321793 64
1777321798 64
1777321803 64
1777321808 64
1777321813 64
1777321818 64
1777321823 64
1777321828 64
1777321833 64
1777321838 64
```
</details>

---

