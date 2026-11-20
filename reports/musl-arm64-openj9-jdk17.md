---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 13:06:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795197717 50
1795197722 50
1795197727 50
1795197732 50
1795197737 50
1795197742 50
1795197747 50
1795197752 50
1795197757 50
1795197762 50
1795197767 50
1795197772 50
1795197777 50
1795197782 50
1795197787 50
1795197792 50
1795197797 50
1795197802 50
1795197807 50
1795197812 50
```
</details>

---

