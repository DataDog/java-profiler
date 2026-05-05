---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-05 06:30:02 EDT

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
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777976657 64
1777976662 64
1777976667 64
1777976672 64
1777976677 64
1777976682 64
1777976687 64
1777976692 64
1777976697 64
1777976702 64
1777976707 64
1777976712 64
1777976717 64
1777976722 64
1777976727 64
1777976732 64
1777976737 64
1777976742 64
1777976747 64
1777976752 64
```
</details>

---

